CC:=gcc
OPTIONS:=-02
LIB_PATH:=-pthread

SRC_DIR:=srS
DST_DIR:=bin

default:
    $(CC) $(OPTIONS) $(LIB_PATH) \
    $(SRC_DIR)/*.c —o $(DST_DIR)/test

clean:
    cd $(DST_DIR); rm test
