APP=pyramid_blending

include ../common.mk

$(APP): $(APP)_opt.so
	rm -f $(APP).so
	ln -s $< $(APP).so
	python main.py ../../images/grand_canyon1.jpg ../../images/grand_canyon2.jpg 11 2048 2048

$(APP)_naive: $(APP)_naive.so
	rm -f $(APP).so
	ln -s $< $(APP).so
	python main.py ../../images/grand_canyon1.jpg ../../images/grand_canyon2.jpg 11 2048 2048

