obj-m +=Platform_device.o
obj-m +=RedLed.o
obj-m +=GreenLed.o
obj-m +=BlueLed.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean
