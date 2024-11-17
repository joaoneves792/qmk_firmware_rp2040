SRC += lib/oled.c \
	   lib/encoder.c \
	   lib/calc.c \
		 grammar/calculator.c \
		 grammar/parser.c

CFLAGS += -Wno-unused-variable -Wno-unused-but-set-variable
