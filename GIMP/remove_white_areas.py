#!/usr/bin/env python
# -*- coding: utf-8 -*-

# Импортируем необходимые модули
from gimpfu import *
#import os, glob, time, math
#import ptvsd

DEBUG = True

def remove_white_regions(image, drawable, threshold=40):
    # Копируем оригинальное изображение на новый слой
    #layer_copy = pdb.gimp_layer_copy(drawable, True)
    layer_copy = drawable.copy()
    layer_copy.name = "Без белого"
    # Добавляем новый слой
    image.add_layer(layer_copy, 0)
    # Start a GIMP undo group to undo the operation in one step
    pdb.gimp_undo_push_group_start(image)
    try:
      # # Получаем размеры изображения
      # width, height = layer_copy.width, layer_copy.height
      # color_to_edit = (255-threshold, 255-threshold, 255-threshold) #or whatever color you wish to edit
      # for i in range(height):
      #   for j in range(width):
      #     num_channels, pixel = pdb.gimp_drawable_get_pixel(layer_copy,i,j)
      #     if all([p > q for p, q in zip(pixel, color_to_edit)]):
      #           pdb.gimp_drawable_set_pixel(layer_copy, i, j, 3, new_color)
      # pdb.gimp_displays_flush()
      
      #Выделяем белые области на слое
      pdb.gimp_by_color_select(drawable, (255, 255, 255), threshold, 0, False, False, 0, False)
      #Удаляем выделенные белые области
      pdb.gimp_edit_clear(layer_copy)
      #This procedure takes no arguments and returns nothing except a success status. Its purpose is to flush all pending updates of image manipulations to the user interface. It should be called whenever appropriate. 
      pdb.gimp_displays_flush()
    finally:
      # End the GIMP undo group
      pdb.gimp_undo_push_group_end(image)
     
register(
            "python-fu-remove-white-regions", # Имя регистрируемой функции
            "Remove white regions and similar colors from the image", # Информация о дополнении
            "Remove white regions and similar colors from the image and create a new layer", # Короткое описание выполняемых скриптом действий
            "Egor Korneev", # Информация об авторе
            "Egor Korneev", # Информация о копирайте
            "8.01.2012", # Дата изготовления
            "Remove White", # Название пункта меню, с помощью которого дополнение будет запускаться
            "*", # Типы изображений с которыми может работать дополнение
            [
                (PF_IMAGE, "image", "Исходное изображение", None), # Указатель на изображение
                (PF_DRAWABLE, "drawable", "Исходный слой", None), # Указатель на слой
                (PF_SLIDER, "threshold", "White Threshold (0-255)", 0, (0, 255, 1))
                
            ],
            [], # Список переменных которые вернет дополнение
            remove_white_regions, menu="<Image>/ТЕСТ/") # Имя исходной функции и меню в которое будет помещён пункт запускающий дополнение

    # Запускаем скрипт
main()