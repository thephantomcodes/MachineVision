import numpy as np
import matplotlib.pyplot as plt

fid = open("img\mri", 'rb');
pic = bytearray(fid.read());
fid.close();

pic = np.reshape(pic, [256, 256]);
print pic.shape
plt.imshow(pic, cmap='gray', vmin=0, vmax=255);
plt.show()
