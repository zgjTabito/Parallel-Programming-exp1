import matplotlib.pyplot as plt
from matplotlib import rcParams

# 设置中文字体（SimHei 是常见的中文黑体，适用于 Windows）
rcParams['font.sans-serif'] = ['SimHei']
rcParams['axes.unicode_minus'] = False  # 解决负号显示为方块的问题


# 数据
n_values = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]
time_com = [33.2773, 135.499, 291.897, 735.631, 1481.24, 2339.08, 5769.18, 6978.31, 10810.9, 12920.6]
time_opt = [32.3927, 128.34, 286.02, 726.1, 1306.53, 1879.84, 5030.25, 5729.02, 9071.17, 11347]

# 画图
plt.figure(figsize=(10, 6))
plt.plot(n_values, time_com, marker='o', label='逐列')
plt.plot(n_values, time_opt, marker='s', label='逐行')
plt.xlabel('n (矩阵维度)')
plt.ylabel('平均运行时间 (ms)')
plt.title('矩阵向量乘法运行时间对比')
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.show()
