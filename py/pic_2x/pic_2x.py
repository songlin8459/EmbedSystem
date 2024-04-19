import os
from PIL import Image

src_dir = "/mnt/ubuntufile/img/"
dst_dir = "/mnt/ubuntufile/img_ret/"

if not os.path.exists(dst_dir):
    os.makedirs(dst_dir)

for file in os.listdir(src_dir):
    if file.endswith(".jpg") or file.endswith(".png"):
        img = Image.open(os.path.join(src_dir, file))
        img = img.resize((img.width * 2, img.height * 2), Image.ANTIALIAS)
        img.save(os.path.join(dst_dir, file))

