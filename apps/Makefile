DIRS = bilateral_grid harris camera_pipe interpolate local_laplacian pyramid_blending unsharp_mask

all: naive polymage

naive:
	    @-for d in $(DIRS); do \
			        make -C $$d naive; \
					        done

polymage:
	    @-for d in $(DIRS); do \
			        make -C $$d polymage; \
					        done

clean:
	    @-for d in $(DIRS); do \
			        make -C $$d clean; \
					        done
		rm -f *.pyc
