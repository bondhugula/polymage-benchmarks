APP=local_laplacian

include ../common.mk

$(APP): $(APP)_opt.so
	rm -f $(APP).so
	ln -s $< $(APP).so
	python main.py ../../images/rgb.png 1 1 11

$(APP)_naive: $(APP)_naive.so
	rm -f $(APP).so
	ln -s $< $(APP).so
	python main.py ../../images/rgb.png 1 1 11

