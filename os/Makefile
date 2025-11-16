all: mbr img

mbr: mbr.S
	nasm -o mbr.bin mbr.S

img: mbr.bin
	dd if=./mbr.bin of=./hd60M.img bs=512 count=1 conv=notrunc

run: mbr img
	qemu-system-x86_64 ./hd60M.img -monitor stdio

dbg: mbr img
	qemu-system-x86_64 ./hd60M.img -s -S -monitor stdio

clean:
	rm *.bin *.img
