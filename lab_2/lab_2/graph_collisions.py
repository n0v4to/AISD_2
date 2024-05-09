import matplotlib.pyplot as plt

table_sizes = [25, 75, 125, 175, 225, 275, 325, 375, 425, 475]
collisions = [571, 243, 150, 111, 87, 76, 51, 42, 40, 34]

plt.figure(figsize=(10, 6))
plt.plot(table_sizes, collisions, marker='o', color='b', linestyle='-', linewidth=2)

plt.title('Зависимость количества коллизий от размера хеш-таблицы')
plt.xlabel('Размер таблицы')
plt.ylabel('Количество коллизий')
plt.grid(True)
plt.xticks(table_sizes)

plt.show()
