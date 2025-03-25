import matplotlib.pyplot as plt
import numpy as np
from matplotlib import rcParams

# 设置中文字体（SimHei 是常见的中文黑体，适用于 Windows）
rcParams['font.sans-serif'] = ['SimHei']
rcParams['axes.unicode_minus'] = False  # 解决负号显示为方块的问题

# 数据：表10中的耗时（单位：ms）
n = [2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536]
sumN_com = [0.08408, 0.08458, 0.15998, 0.35336, 0.83644, 1.46366, 3.06324, 7.1479,
            15.0029, 29.1939, 59.6842, 121.46, 245.202, 842.001, 1713.94, 2317.95]
sumN_opt2 = [0.11042, 0.19884, 0.48826, 0.54342, 1.41088, 1.92696, 3.61364, 8.36702,
             13.1639, 26.0629, 58.3305, 122.486, 386.696, 836.295, 1657.75, 4297.8]
sumN_opt4 = [0.17814, 0.21404, 0.4278, 0.60814, 1.08158, 2.78702, 5.0029, 9.7741,
             13.2219, 26.0553, 57.6475, 111.001, 380.695, 756.898, 1475.95, 5489.22]
sumN_opt2_unrolled = [0.04706, 0.08618, 0.11614, 0.22606, 0.47582, 0.92954, 1.70096,
                      3.45454, 8.31612, 16.4756, 33.7793, 68.2585, 187.71, 380.175,
                      776.839, 1608.27]
sumN_opt4_unrolled = [0.0586, 0.08106, 0.15078, 0.18884, 0.52662, 0.7048, 1.36096,
                      2.4289, 4.71282, 10.0959, 17.497, 41.1388, 120.888, 238.85,
                      474.234, 968.573]

# 计算加速比：Speedup = 原始时间 / 优化时间
def calculate_speedup(original, optimized):
    return np.array(original) / np.array(optimized)

# 计算加速比
speedup_opt2 = calculate_speedup(sumN_com, sumN_opt2)
speedup_opt4 = calculate_speedup(sumN_com, sumN_opt4)
speedup_opt2_unrolled = calculate_speedup(sumN_com, sumN_opt2_unrolled)
speedup_opt4_unrolled = calculate_speedup(sumN_com, sumN_opt4_unrolled)

# 绘制加速比图
plt.figure(figsize=(10, 6))

# 绘制不同算法的加速比
plt.plot(n, speedup_opt2, marker='o', label="sumN_opt2 (加速比)", linestyle='-', color='b')
plt.plot(n, speedup_opt4, marker='s', label="sumN_opt4 (加速比)", linestyle='-', color='g')
plt.plot(n, speedup_opt2_unrolled, marker='^', label="sumN_opt2_unrolled (加速比)", linestyle='-', color='r')
plt.plot(n, speedup_opt4_unrolled, marker='D', label="sumN_opt4_unrolled (加速比)", linestyle='-', color='c')

# 设置坐标轴标签与标题
plt.xlabel("数组规模n")
plt.ylabel("加速比 ")
plt.xscale("log", base=2)
plt.legend()
plt.grid(True)
plt.xticks(n, rotation=45)
plt.tight_layout()

# 显示图形
plt.show()
