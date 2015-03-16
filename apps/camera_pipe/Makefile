APP=camera_pipe

include ../common.mk

$(APP): $(APP)_opt.so
	rm -f $(APP).so
	ln -s $< $(APP).so
	python main.py 3700 50 2.0 11

$(APP)_naive: $(APP)_naive.so
	rm -f $(APP).so
	ln -s $< $(APP).so
	python main.py 3700 50 2.0 11
