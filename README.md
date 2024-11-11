# About

Пример простой генерации трёхмерной графики типа Wolf3D, написанный на Си во время обучения в Школе 21

Для отрисовки графики используется метод Ray casting: преобразуем план этажа (карту) в 3D-проекцию путем "бросания лучей" из точки обзора по всей области видимости

Запускается с файлом карты, который содержит информацию о ресурсах и карту лабиринта

https://github.com/user-attachments/assets/7f1b8836-6060-436e-bf1d-6fb7f651551e

# Clone and compile project

```
make
```

# Run

```
./cub3D map.cub
```

# Available maps

map0.cub - mini 1024x768  
map.cub - 1920x1080, different sprites  
map3.cub  
map4.cub  
map5.cub

# Interface keys

ESC - exit  
Tab - toggle minimap  
1 - no textures  
2 - gradient textures  
3 - image textures  
4 - toggle sprites  
5 - toggle walls collision

# Movement keys

w - move front  
s - move back  
a - strafe left  
d - strafe right  
<- - turn left  
-> - turn right
