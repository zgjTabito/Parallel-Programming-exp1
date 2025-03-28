import matplotlib.pyplot as plt
from matplotlib import rcParams

# 设置中文字体（SimHei 是常见的中文黑体，适用于 Windows）
rcParams['font.sans-serif'] = ['SimHei']
rcParams['axes.unicode_minus'] = False  # 解决负号显示为方块的问题
# 数据
n = [2, 4, 8, 16, 32, 64, 128, 256, 512, 1024,
     2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144]
sumN_com = [0.0798, 0.12528, 0.26178, 0.5244, 1.15416, 2.58278, 4.74218, 7.75302,
            15.1731, 23.8941, 51.9907, 92.7806, 198.171, 417.453, 848.268, 1506.68, 3496.64, 7328.71]
# 无循环展开的 2 路链式求和
sumN_opt2 = [0.14142, 0.2558, 0.3635, 0.71084, 0.836, 2.42958, 4.0466, 6.24006,
             9.7038, 18.7528, 42.6455, 83.4118, 157.25, 322.242, 665.655, 1429.68, 2618.63, 5228.48]
# 无循环展开的 4 路链式求和
sumN_opt4 = [0.22552, 0.30642, 0.399, 0.69212, 0.76278, 2.49118, 2.77064, 5.87162,
             9.17856, 17.7294, 42.3089, 68.2044, 148.32, 290.797, 678.92, 1334.75, 2364.26, 5023.27]

sumN_opt2_unrolled = [0.06374, 0.14506, 0.1799, 0.3254, 0.44334, 1.24706, 2.14022, 3.764,
                      6.24176, 13.8008, 29.2442, 50.3182, 110.371, 203.094, 468.273, 840.934, 1723.72, 3588.92]

sumN_opt4_unrolled = [0.08584, 0.0947, 0.14292, 0.26282, 0.26694, 1.02024, 1.84302, 2.61802,
                      3.56152, 7.35694, 16.6618, 26.594, 63.8615, 110.027, 253.298, 536.525, 1062.54, 2123.99]

# 绘图
plt.figure(figsize=(10, 6))

plt.plot(n, sumN_opt2, marker='o', label='2路链式求和（不展开）')
plt.plot(n, sumN_opt2_unrolled, marker='o', linestyle='--', label='2路链式求和循环展开')

plt.plot(n, sumN_opt4, marker='s', label='4路链式求和（不展开）')
plt.plot(n, sumN_opt4_unrolled, marker='s', linestyle='--', label='4路链式求和循环展开')

plt.xscale("log", base=2)
plt.xlabel("数据规模n")
plt.ylabel("时间 (ms)")
plt.legend()
plt.grid(True)
plt.xticks(n, rotation=45)
plt.tight_layout()
plt.show()
