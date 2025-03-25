import matplotlib.pyplot as plt
from matplotlib import rcParams

# 设置中文字体（SimHei 是常见的中文黑体，适用于 Windows）
rcParams['font.sans-serif'] = ['SimHei']
rcParams['axes.unicode_minus'] = False  # 解决负号显示为方块的问题
# 数据
n = [2, 4, 8, 16, 32, 64, 128, 256, 512, 1024,
     2048, 4096, 8192, 16384, 32768, 65536]

# 原始未展开
sumN_opt2 = [0.11042, 0.19884, 0.48826, 0.54342, 1.41088, 1.92696, 3.61364, 8.36702,
             13.1639, 26.0629, 58.3305, 122.486, 386.696, 836.295, 1657.75, 4297.8]
sumN_opt4 = [0.17814, 0.21404, 0.4278, 0.60814, 1.08158, 2.78702, 5.0029, 9.7741,
             13.2219, 26.0553, 57.6475, 111.001, 380.695, 756.898, 1475.95, 5489.22]

# 循环展开版本
sumN_opt2_unrolled = [0.04706, 0.08618, 0.11614, 0.22606, 0.47582, 0.92954, 1.70096,
                      3.45454, 8.31612, 16.4756, 33.7793, 68.2585, 187.71, 380.175, 776.839, 1608.27]
sumN_opt4_unrolled = [0.0586, 0.08106, 0.15078, 0.18884, 0.52662, 0.7048, 1.36096,
                      2.4289, 4.71282, 10.0959, 17.497, 41.1388, 120.888, 238.85, 474.234, 968.573]

# 绘图
plt.figure(figsize=(10, 6))

plt.plot(n, sumN_opt2, marker='o', label='sumN_opt2 (原始)')
plt.plot(n, sumN_opt2_unrolled, marker='o', linestyle='--', label='sumN_opt2_unrolled')

plt.plot(n, sumN_opt4, marker='s', label='sumN_opt4 (原始)')
plt.plot(n, sumN_opt4_unrolled, marker='s', linestyle='--', label='sumN_opt4_unrolled')

plt.xscale("log", base=2)
plt.xlabel("数据规模n")
plt.ylabel("时间 (ms)")
plt.legend()
plt.grid(True)
plt.xticks(n, rotation=45)
plt.tight_layout()
plt.show()
