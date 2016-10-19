
TOP =  ../../../..

include $(TOP)/mk/common.mk

OUTPUT = pl

# hal sources
HAL_DIR = $(TOP)/board/st/stm32f4/hal/src
SRC += $(HAL_DIR)/stm32f4xx_hal.c \
       $(HAL_DIR)/stm32f4xx_hal_rcc.c \
       $(HAL_DIR)/stm32f4xx_hal_cortex.c \
       $(HAL_DIR)/stm32f4xx_hal_gpio.c \
#       $(HAL_DIR)/stm32f4xx_hal_tim.c \
#       $(HAL_DIR)/stm32f4xx_hal_tim_ex.c \

# board sources
BOARD_DIR = $(TOP)/board/st/stm32f4/mb997
SRC += $(BOARD_DIR)/main.c \
       $(BOARD_DIR)/system_stm32f4xx.c \
       $(BOARD_DIR)/stm32f4xx_it.c \
       $(BOARD_DIR)/syscalls.c \
       $(BOARD_DIR)/gpio.c \
       $(BOARD_DIR)/debounce.c \
       $(BOARD_DIR)/usart.c \

OBJ = $(patsubst %.c, %.o, $(SRC))
OBJ += $(BOARD_DIR)/start.o

# include files
INC = .
INC += $(TOP)/board/st/stm32f4/cmsis
INC += $(TOP)/board/st/stm32f4/hal/inc

INCLUDE = $(addprefix -I,$(INC))

# compiler flags
X_CFLAGS += -Wno-unused-parameter

# linker flags
LDSCRIPT = stm32f407vg_flash.ld
X_LDFLAGS = -T$(LDSCRIPT) -Wl,-Map,$(OUTPUT).map -Wl,--gc-sections
X_LDFLAGS += -L$(TOP)/picolisp/miniPicoLisp/src

# defines
DEFINES = -DSTM32F407xx

.S.o:
	$(X_GCC) $(INCLUDE) $(DEFINES) $(X_CFLAGS) -c $< -o $@
.c.o:
	$(X_GCC) $(INCLUDE) $(DEFINES) $(X_CFLAGS) -c $< -o $@

.PHONY: all clean

all: $(OBJ)
	$(X_GCC) $(X_CFLAGS) $(X_LDFLAGS) $(OBJ) -lm -lpicolisp -o $(OUTPUT)
	$(X_OBJCOPY) -O binary $(OUTPUT) $(OUTPUT).bin

clean:
	-rm $(OBJ)	
	-rm $(OUTPUT)
	-rm $(OUTPUT).map	
	-rm $(OUTPUT).bin	

