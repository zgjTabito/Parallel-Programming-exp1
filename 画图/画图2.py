import matplotlib.pyplot as plt
from matplotlib import rcParams

# 设置中文字体（SimHei 是常见的中文黑体，适用于 Windows）
rcParams['font.sans-serif'] = ['SimHei']
rcParams['axes.unicode_minus'] = False  # 解决负号显示为方块的问题


# 数据
n = [2, 4, 8, 16, 32, 64, 128, 256, 512, 1024,
     2048, 4096, 8192, 16384, 32768]
sumN_com = [0.08408, 0.08458, 0.15998, 0.35336, 0.83644, 1.46366, 3.06324, 7.1479,
            15.0029, 29.1939, 59.6842, 121.46, 245.202, 842.001, 1713.94]
sumN_rec = [0.0964, 0.11638, 0.2171, 0.48952, 0.94128, 1.95542, 4.36884, 9.1067,
            15.6106, 32.0558, 54.9409, 111.444, 382.013, 767.32, 1512.3]
sumN_opt2 = [0.11042, 0.19884, 0.48826, 0.54342, 1.41088, 1.92696, 3.61364, 8.36702,
             13.1639, 26.0629, 58.3305, 122.486, 386.696, 836.295, 1657.75]
sumN_opt4 = [0.17814, 0.21404, 0.4278, 0.60814, 1.08158, 2.78702, 5.0029, 9.7741,
             13.2219, 26.0553, 57.6475, 111.001, 380.695, 756.898, 1475.95]

# 绘图
plt.figure(figsize=(10, 6))
plt.plot(n, sumN_com, marker='o', label='sumN_com')
plt.plot(n, sumN_rec, marker='s', label='sumN_recursion')
plt.plot(n, sumN_opt2, marker='^', label='sumN_opt2')
plt.plot(n, sumN_opt4, marker='D', label='sumN_opt4')

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

