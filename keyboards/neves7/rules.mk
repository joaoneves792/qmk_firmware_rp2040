SRC += lib/oled.c \
	   lib/encoder.c \
	   lib/calc.c \
		 lib/printf.c \
		 grammar/calculator.c \
		 grammar/parser.c

CFLAGS += -Wno-unused-variable -Wno-unused-but-set-variable
AUTO_SHIFT_ENABLE = yes
DEBOUNCE_TYPE = sym_defer_pk
