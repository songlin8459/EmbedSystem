v4l2-ctl -d /dev/video22 --set-fmt-video=width=640,height=480,pixelformat=NV12 --stream-mmap=3 --stream-to=out.yuv --stream-skip=9 --stream-count=1

./yuv_to_jpg
