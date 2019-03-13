# SeamVideoCUDA_2_improves
基于缝合线及多频带融合的两路视频拼接，运用CUDA加速，可实时部署
<br><br>
处理流程：
1.对每张图进行特征点提取
<br>
2.对对特征点进行匹配
<br>
3.进行图像配准
<br>
4.把图像拷贝到另一幅图像的特定位置
<br>
5.对重叠边界进行特殊处理
<br>
用SIFT算法来实现图像拼接是很常用的方法，但是因为SIFT计算量很大，所以在速度要求很高的场合下不再适用。
SURF在速度方面有了明显的提高（速度是SIFT的3倍）
<br><br>
得到了两幅待拼接图的匹配点集，接下来我们进行图像的配准，即将两张图像转换为同一坐标下findHomography
<br><br>

多波段融合的基本思想是图像可以分解为不同频率的图像的叠加（类似于傅里叶变换），在不同的频率上，应该使用不同的权重来进行融合，
在低频部分应该使用波长较宽的加权信号（例如高斯核函数中sigma比较大），在高频部分应该使用较窄的加权信号（例如高斯核函数的sigma比较小），其算法如下：
<br>
1.计算输入图像的高斯金字塔。
<br>
2.计算输入图像的拉普拉斯金字塔。
<br>
3.将处于同一级的拉普拉斯金字塔进行融合。例如在拼接缝两侧使用简单的线性融合。记输出图像为，则这里得到
<br>
4.将高层的拉普拉斯金字塔依次扩展直至和相同分辨率。我们记做
<br>
5.将4中得到的图像依次叠加，则得到最终的输出图像。

<br><br>
左图：
<br><br>
![Image text](https://github.com/hujinxinb/SeamVideoCUDA_2_improves/blob/master/img/11.jpg)
<br><br>
右图：
<br><br>
![Image text](https://github.com/hujinxinb/SeamVideoCUDA_2_improves/blob/master/img/12.jpg)
<br><br>
拼接结果：
<br><br>
![Image text](https://github.com/hujinxinb/SeamVideoCUDA_2_improves/blob/master/img/13.jpg)
