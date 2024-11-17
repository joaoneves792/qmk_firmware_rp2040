SRC += lib/oled.c \
	   lib/encoder.c \
	   lib/calc.c \
		 ragellemon/calculator.c \
		 ragellemon/parser.c

CFLAGS += -Wno-unused-variable -Wno-unused-but-set-variable -Wno-strict-prototypes
