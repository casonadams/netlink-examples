# netlink-examples

## Make

```bash
make
```

## insmod kernel module

```bash
sudo insmod netlinkKernel.ko
```

## Run in sperate shells

```bash
./recv
```

```bash
./send
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

