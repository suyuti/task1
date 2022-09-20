docker run -it --rm --name=nxlog \
    --mount type=bind,source=${PWD}/src,target=/src \
	nxlog/nxlog_build:0.1 \
	bash