# netlink-examples

## Make

```bash
make
```

## Compile

```bash
gcc netlinkUser.c -o netlinkUser
```

## insmod kernel module

```bash
sudo insmod netlinkKernel.ko
```

## Run

```bash
./netlinkUser
```

## Validation

```bash
dmesg
```

## Clean up

### rmmod kernel module

```bash
sudo rmmod netlinkKernel
```

### Clean

```bash
make clean
```

