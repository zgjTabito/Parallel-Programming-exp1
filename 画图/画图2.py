import matplotlib.pyplot as plt
from matplotlib import rcParams

# 设置中文字体（SimHei 是常见的中文黑体，适用于 Windows）
rcParams['font.sans-serif'] = ['SimHei']
rcParams['axes.unicode_minus'] = False  # 解决负号显示为方块的问题


# 数据
n = [2, 4, 8, 16, 32, 64, 128, 256, 512, 1024,
     2048, 4096, 8192, 16384, 32768, 65536, 131072, 262144]
sumN_com = [0.0798, 0.12528, 0.26178, 0.5244, 1.15416, 1.03728, 4.74218, 7.75302,
            15.1731, 23.8941, 51.9907, 92.7806, 198.171, 417.453, 848.268, 1506.68, 3496.64, 7328.71]
sumN_rec = [0.07916, 0.15468, 0.33926, 0.80318, 0.97264, 1.7097, 5.4213, 7.70776,
            13.5507, 22.4193, 49.6116, 74.5849, 164.742, 302.634, 628.353, 1362.87, 2602.79, 5292.33]
# 无循环展开的 2 路链式求和
sumN_opt2 = [0.14142, 0.2558, 0.3635, 0.71084, 0.836, 2.42958, 4.0466, 6.24006,
             9.7038, 18.7528, 42.6455, 83.4118, 157.25, 322.242, 665.655, 1429.68, 2618.63, 5228.48]
# 无循环展开的 4 路链式求和
sumN_opt4 = [0.22552, 0.30642, 0.399, 0.69212, 0.76278, 2.69118, 2.77064, 5.87162,
             9.17856, 17.7294, 42.3089, 68.2044, 148.32, 290.797, 678.92, 1334.75, 2364.26, 5023.27]

# 绘图
plt.figure(figsize=(10, 6))
plt.plot(n, sumN_com, marker='o', label='平凡求和')
plt.plot(n, sumN_rec, marker='s', label='递归算法')
plt.plot(n, sumN_opt2, marker='^', label='2路链式算法')
plt.plot(n, sumN_opt4, marker='D', label='4路链式算法')

# 坐标轴与标签
plt.xlabel("数据规模n")
plt.ylabel("时间(ms)")
plt.xscale("log", base=2)
plt.grid(True, linestyle="--", linewidth=0.5)
plt.legend()

# 设置横坐标刻度均匀可读
plt.xticks(n, rotation=45)
plt.tight_layout()
plt.show()
