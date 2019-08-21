#include <sys/socket.h>
#include <linux/netlink.h>
#include <stdio.h>
#include <malloc.h>
#include <stdio.h>

#define MAX_PAYLOAD 1024
#define NETLINK_USER 31

struct sockaddr_nl src_addr;
struct sockaddr_nl dest_addr;
struct nlmsghdr *nlh = NULL;
struct iovec iov;
struct msghdr msg;
int fd;

int main() {
    fd = socket(PF_NETLINK, SOCK_RAW, NETLINK_USER);
    printf("Inside send main\n");

    if (fd < 0) {
        printf("Socket creation failed. try again\n");
        return -1;
    }

    memset(&src_addr, 0, sizeof(src_addr));
    src_addr.nl_family = AF_NETLINK;
    src_addr.nl_pid = getpid();
    src_addr.nl_groups = 0;

    bind(fd, (struct sockaddr *)&src_addr, sizeof(src_addr));

    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.nl_family = AF_NETLINK;
    dest_addr.nl_pid = 0;
    dest_addr.nl_groups = 0;

    nlh = (struct nlmsghdr *)malloc(NLMSG_SPACE(MAX_PAYLOAD));
    memset(nlh, 0, NLMSG_SPACE(MAX_PAYLOAD));
    nlh->nlmsg_len = NLMSG_SPACE(MAX_PAYLOAD);
    nlh->nlmsg_pid = getpid();
    nlh->nlmsg_flags = 0;

    strcpy(NLMSG_DATA(nlh), " --> Space 001 <--");

    iov.iov_base = (void *)nlh;
    iov.iov_len = nlh->nlmsg_len;
    msg.msg_name = (void *)&dest_addr;
    msg.msg_namelen = sizeof(dest_addr);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;

    //send the message
    sendmsg(fd, &msg, 0);
    printf("Send message %s\n", (char *)NLMSG_DATA(nlh));
    /* Read message from kernel */
    recvmsg(fd, &msg, 0);
    printf("Received message payload: %s\n", (char *)NLMSG_DATA(nlh));

    close(fd);
}
