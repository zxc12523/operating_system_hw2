# operating_system_hw2

- Virtual Memory:
    - An isolated and abstracted memory space for each process.
    - A portion of VM pages are mapped to physical memory through per-process page table.
- Swapping :
    - Allow VM pages not only mapped to physical memory pages, can also be mapped to
blocks on a disk.
    - The OS can swap out “cold” memory pages to disk blocks, or swap in disk blocks to physical memory when needed.

## Launching

```shell
docker pull ntuos/mp2
docker run -it -v $(pwd):/xv6 ntus/mp2
cat /etc/os-release
```

## Testing

1. Run the command to launch all tests at once, and the output will be saved to mp2_N.out files.
```shell
./run_mp2.py
```
2. To run an individual test program instead, run “make qemu” to enter the xv6 shell and “runmp2_N”.
```shell
make clean
make qemu
```