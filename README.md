
git clone https://github.com/tailscale/tailscale
add function and call get_myuser_function in:   /root/.cache/tailscale-go/src/net/fd_unix.go
build with: ./build_dist_test.sh  tailscale.com/cmd/tailscaled

RUN

[tailscale]# ./tailscaled 
logtail started
Program starting: v1.37.73-t99b9d7a62, Go 1.20rc3-tsd0f872e: []string{"./tailscaled"}
LogID: 54d24c823eb398b50316aeac522409d4dacc00eac0ff4b9d7c324b36287329c5
logpolicy: using system state directory "/var/lib/tailscale"
curUser:%s
 0x186cb30
fatal error: unexpected signal during runtime execution
[signal SIGSEGV: segmentation violation code=0x1 addr=0xe5 pc=0x7f1bc072abd0]

runtime stack:
runtime.throw({0xf5d2f2?, 0x7f1bc002c490?})
	/root/.cache/tailscale-go/src/runtime/panic.go:1047 +0x5d fp=0x7f1bc2b1fb40 sp=0x7f1bc2b1fb10 pc=0x43751d
runtime.sigpanic()
	/root/.cache/tailscale-go/src/runtime/signal_unix.go:821 +0x3e9 fp=0x7f1bc2b1fba0 sp=0x7f1bc2b1fb40 pc=0x44e6a9


]# gdb ./tailscaled 
GNU gdb (GDB) Red Hat Enterprise Linux 8.2-19.el8
Copyright (C) 2018 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-redhat-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from ./tailscaled...done.
warning: File "/root/.cache/tailscale-go/src/runtime/runtime-gdb.py" auto-loading has been declined by your `auto-load safe-path' set to "$debugdir:$datadir/auto-load".
To enable execution of this file add
	add-auto-load-safe-path /root/.cache/tailscale-go/src/runtime/runtime-gdb.py
line to your configuration file "/root/.gdbinit".
To completely disable this security protection add
	set auto-load safe-path /
line to your configuration file "/root/.gdbinit".
For more information about this security protection see the
"Auto-loading safe path" section in the GDB manual.  E.g., run from the shell:
	info "(gdb)Auto-loading safe path"
(gdb) r
Starting program: /home/xxxx/tailscale/tailscaled 
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib64/libthread_db.so.1".
[New Thread 0x7fffd0c63700 (LWP 17727)]
[New Thread 0x7fffcbfff700 (LWP 17728)]
[New Thread 0x7fffcb7fe700 (LWP 17729)]
[New Thread 0x7fffcaffd700 (LWP 17730)]
[New Thread 0x7fffca7fc700 (LWP 17731)]
logtail started
Program starting: v1.37.73-t99b9d7a62, Go 1.20rc3-tsd0f872e: []string{"/home/xxxxx/tailscale/tailscaled"}
LogID: 54d24c823eb398b50316aeac522409d4dacc00eac0ff4b9d7c324b36287329c5
logpolicy: using system state directory "/var/lib/tailscale"
curUser:%s
 0x186cb30
[New Thread 0x7fffc9ffb700 (LWP 17732)]

Thread 5 "tailscaled" received signal SIGSEGV, Segmentation fault.
[Switching to Thread 0x7fffcaffd700 (LWP 17730)]
0x00007fffd00b0bd0 in __nss_readline (fp=0x7fffc9105490, buf=0x7fffcaffcd60 "root:x:0:0:root:/root:/bin/bash\n", len=<optimized out>, poffset=0x7fffcaffcbf0) at ./nss_readline.c:68
68	      while (isspace (*p))
(gdb) info sharedlibrary
From                To                  Syms Read   Shared Object Library
0x00007fffd00aa7b0  0x00007fffd00b0d32  Yes         /lib64/libnss_files.so.2
0x00007fffc9457c80  0x00007fffc95a3d7d  Yes         /lib64/libc.so.6
0x00007fffc9206050  0x00007fffc9228ff2  Yes         /lib64/ld-linux-x86-64.so.2
(gdb) bt
#0  0x00007fffd00b0bd0 in __nss_readline (fp=0x7fffc9105490, buf=0x7fffcaffcd60 "root:x:0:0:root:/root:/bin/bash\n", len=<optimized out>, poffset=0x7fffcaffcbf0) at ./nss_readline.c:68
#1  0x00007fffd00adc1f in internal_getent (stream=0x7fffc9105490, result=result@entry=0x7fffcaffcd30, buffer=buffer@entry=0x7fffcaffcd60 "root:x:0:0:root:/root:/bin/bash\n", buflen=buflen@entry=1024, 
    errnop=errnop@entry=0x7fffcaffd6a8) at nss_files/files-XXX.c:152
#2  0x00007fffd00adff3 in _nss_files_getpwuid_r (uid=0, result=0x7fffcaffcd30, buffer=0x7fffcaffcd60 "root:x:0:0:root:/root:/bin/bash\n", buflen=1024, errnop=0x7fffcaffd6a8) at nss_files/files-pwd.c:39
#3  0x0000000000cd0eed in getpwuid_r ()
#4  0x0000000000c7f742 in cuserid ()
#5  0x0000000000c71bb8 in get_myuser_function ()
#6  0x0000000000c5de26 in _cgo_aa5f6bc90aaf_Cfunc_get_myuser_function (v=0xc000197b30) at cgo-gcc-prolog:51
#7  0x000000000046d364 in runtime.asmcgocall () at /root/.cache/tailscale-go/src/runtime/asm_amd64.s:848
#8  0x000000000000000b in ?? ()
#9  0x000000c000007ba0 in ?? ()
#10 0x000000c000198060 in ?? ()
#11 0x000000000046f7a6 in time.now () at /root/.cache/tailscale-go/src/runtime/time_linux_amd64.s:52
#12 0x000000002744a1fb in ?? ()
#13 0x0000000000000280 in ?? ()
#14 0x01007fffc0000020 in ?? ()
#15 0x0000000000800000 in regexp/syntax.(*parser).parseUnicodeClass (p=0x8854d244c4649b4e, s=..., r=<error reading variable: access outside bounds of object referenced via synthetic pointer>, out=..., 
    rest=..., err=...) at /root/.cache/tailscale-go/src/regexp/syntax/parse.go:1700
#16 0x00007fffcaffd700 in ?? ()
#17 0x8854d244c4649b4e in ?? ()
#18 0x00007fffcbffedde in ?? ()
#19 0x00007fffcbffeddf in ?? ()
#20 0x00007fffcbffeed0 in ?? ()
#21 0x00007fffcaffd340 in ?? ()
#22 0x77ab47bb61649b4e in ?? ()
#23 0x8854d3c876569b4e in ?? ()
#24 0x0000000000000000 in ?? ()
(gdb) 

