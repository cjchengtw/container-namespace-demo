# container-namespace-demo

gcc -Wall 程式名稱.c -o 程式名稱.o


## ipc

host: ipcmk -Q
containe: ipcs -q
sudo ./ipc_namespace

## pid

mount -t proc proc /proc

推出再執行一次
