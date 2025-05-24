all: testing-shaders http-api-rendering integration-testing

clean:
	@rm -rf build

integration-testing:
	@mkdir -p build
	@g++ \
		-Ilib \
		-Llib \
		./integration-testing/game.cpp \
		./integration-testing/platform-pc.cpp \
		./integration-testing/main.cpp \
		-lraylib \
		-o ./build/game

	@g++ \
		-Ilib \
		-Icommon \
		-Llib \
		./integration-testing/game.cpp \
		./integration-testing/platform-test.cpp \
		./integration-testing/game.test.cpp \
		./common/image-compare.cpp \
		-g \
		-lraylib \
		`pkg-config --cflags --libs MagickWand` \
		-o ./build/game-test
	@./build/game-test

http-api-rendering:
	@mkdir -p build
	@g++ \
		-Ilib \
		-Icommon \
		-Llib \
		./common/render.cpp \
		./http-api-rendering/main.cpp \
		-lraylib \
		-o ./build/http-api-rendering

testing-shaders:
	@mkdir -p build
	@g++ \
		-Ilib \
		-Icommon \
		-I/usr/include/ImageMagick-6 \
		-I/usr/include/x86_64-linux-gnu/ImageMagick-6 \
		-Llib \
		./common/render.cpp \
		./common/image-compare.cpp \
		./testing-shaders/shader.test.cpp \
		./testing-shaders/verify.cpp \
		-lraylib \
		`pkg-config --cflags --libs MagickWand` \
		-o ./build/shader-test
	@./build/shader-test

.PHONY: all testing-shaders http-api-rendering integration-testing clean
