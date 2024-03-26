# LDD-note

# Chap. 3

After getting the `scull.ko`, use `scull_load` & `scull_unload` instead of `insmod` & `rmmod`, else there's no entry created in `/dev`.

`scull_load` does:

- invoke `insmod` to install the module
- retrive major number from `/proc/devices` using `awk`
- invoke `mknod` to create a character device in `/dev`

then try `dd if=/dev/zero of=/dev/scull`, look at `htop` to see how this fill up your memory. To release, use `echo 123 > /dev/scull`, because scull simply free all memory when it's opened for write.

Use `scull_unload` to remove the module.

About `mknod`:

```
# man: mknod [OPTION]... NAME TYPE [MAJOR MINOR]
mknod /dev/${device}0 c $major 0
mknod /dev/${device}1 c $major 1
mknod /dev/${device}2 c $major 2
mknod /dev/${device}3 c $major 3
```

`mknod` creates character(TYPE=c, u), block(TYPE=b) devices in `/dev`. It's also used to create FIFO(TYPE=p).

# Chap. 4

### The circular buffer for log

`printk` writes to a circular buffer, then wakes any process that is sleeping in the `syslog(2)` system call or that is reading /proc/kmsg.

These two interfaces to the logging engine are almost equivalent, but note that reading from /proc/kmsg consumes the data from the log buffer, whereas the `syslog(2)` system call can optionally return log data while leaving it for other processes as well.

The `dmesg` command can be used to look at the content of the buffer without flushing it.

### klogd & syslogd

On arch linux, I did not find a way to install klogd, but note `journalctl -f` shows the log.

In general, reading the /proc file is easier and is the default behavior for klogd.

If the klogd process is running, it retrieves kernel messages and dispatches them to syslogd, which in turn checks /etc/syslog.conf to find out how to deal with them.

Disadvantage of syslogd: it writes to file a lot, if there are too many `printk` calls the system slows down easily.

Note: `syslog(2)` system call talks to printk() buffer, while `syslog(3)` C library function talks to syslogd.

### Oops message

Load ldd3/misc-modules/faulty.ko, and `echo 123 > /dev/faulty`, the `journalctl -f` outputs:

```
Mar 05 08:46:01 garch kernel: BUG: kernel NULL pointer dereference, address: 0000000000000000
Mar 05 08:46:01 garch kernel: #PF: supervisor write access in kernel mode
Mar 05 08:46:01 garch kernel: #PF: error_code(0x0002) - not-present page
Mar 05 08:46:01 garch kernel: PGD 0 P4D 0
Mar 05 08:46:01 garch kernel: Oops: 0002 [#4] PREEMPT SMP NOPTI
Mar 05 08:46:01 garch kernel: CPU: 7 PID: 6994 Comm: zsh Tainted: P      D    OE      6.7.8-arch1-1 #1 dafab5364db1ad2baad864a7454abc1e303295d4
Mar 05 08:46:01 garch kernel: Hardware name: HUAWEI KLVC-WXX9/KLVC-WXX9-PCB, BIOS 1.25 04/20/2021
Mar 05 08:46:01 garch kernel: RIP: 0010:faulty_write+0x9/0x20 [faulty]
Mar 05 08:46:01 garch kernel: Code: Unable to access opcode bytes at 0xffffffffc5d1cfef.
Mar 05 08:46:01 garch kernel: RSP: 0018:ffffbd9503ec3e40 EFLAGS: 00010282
Mar 05 08:46:01 garch kernel: RAX: ffffffffc5d1d010 RBX: 0000000000000004 RCX: ffffbd9503ec3ee0
Mar 05 08:46:01 garch kernel: RDX: 0000000000000004 RSI: 00006021db73bc80 RDI: ffff9bb8a2dfd600
Mar 05 08:46:01 garch kernel: RBP: 0000000000000000 R08: 0000000000000000 R09: 0000000000000000
Mar 05 08:46:01 garch kernel: R10: 0000000000000000 R11: 0000000000000000 R12: 00006021db73bc80
Mar 05 08:46:01 garch kernel: R13: ffff9bb8a2dfd600 R14: ffffbd9503ec3ee0 R15: 0000000000000000
Mar 05 08:46:01 garch kernel: FS:  00007c3f635a8080(0000) GS:ffff9bb9da7c0000(0000) knlGS:0000000000000000
Mar 05 08:46:01 garch kernel: CS:  0010 DS: 0000 ES: 0000 CR0: 0000000080050033
Mar 05 08:46:01 garch kernel: CR2: ffffffffc5d1cfef CR3: 000000018aff8002 CR4: 00000000003706f0
Mar 05 08:46:01 garch kernel: Call Trace:
Mar 05 08:46:01 garch kernel:  <TASK>
Mar 05 08:46:01 garch kernel:  ? __die+0x23/0x70
Mar 05 08:46:01 garch kernel:  ? page_fault_oops+0x171/0x4e0
Mar 05 08:46:01 garch kernel:  ? exc_page_fault+0x7f/0x180
Mar 05 08:46:01 garch kernel:  ? asm_exc_page_fault+0x26/0x30
Mar 05 08:46:01 garch kernel:  ? __pfx_faulty_write+0x10/0x10 [faulty 1adfbb7c06cce454a6172d07d4c8db4cb80321c1]
Mar 05 08:46:01 garch kernel:  ? faulty_write+0x9/0x20 [faulty 1adfbb7c06cce454a6172d07d4c8db4cb80321c1]
Mar 05 08:46:01 garch kernel:  vfs_write+0xef/0x400
...
```

(note the `faulty_write` in Call Trace)

and zsh gets killed after this operation.

