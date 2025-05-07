all: testing-shaders

testing-shaders:
	@mkdir -p build
	@g++ \
		-Ilib \
		-I/usr/include/ImageMagick-6 \
		-I/usr/include/x86_64-linux-gnu/ImageMagick-6 \
		-Llib \
		./testing-shaders/shader.test.cpp \
		./testing-shaders/verify.cpp \
		./testing-shaders/render.cpp \
		./testing-shaders/image-compare.cpp \
		-lraylib \
		`pkg-config --cflags --libs MagickWand` \
		-o ./build/shader-test
	@./build/shader-test

.PHONY: all testing-shaders
