import numpy as np
import numpy.random as rand
import pandas as pd

matrix = np.array(rand.randint(0, 10, (8,8,2)))

#приводим к симметричному виду
for i in range(8):
    for j in range(8):
        if i == j:
            matrix[i,j,0] = 0
            matrix[i,j,1] = 0
        matrix[i,j,0] = matrix[j,i,1]
        matrix[i,j,1] = matrix[j,i,0]

score = [0]*8
for i in range(8):
    score[i]=matrix[i].sum(axis=0)[0]

#подсчет места команды в рейтинге 'Place'
#как упростить этот момент или сделать эффективнее?
num_score = [[score[i], i] for i in range(8)]
num_score = sorted(num_score, key=lambda i: i[0], reverse = True)
places = [0]*8
place = 1
for i in range(7):
    index = num_score[i][1]
    places[index] = place
    #можем присваивать одинаковые места за одинаковые очки
    if (num_score[i][0] != num_score[i+1][0]):
        place += 1
index = num_score[7][1]
places[index] = place

#форматирование массива для использования pandas
container_for_print = [[0] * 8 for i in range(8)]
for i in range(8):
    for j in range(8):
        string = str(matrix[i,j,0]) + ':' + str(matrix[i,j,1])
        container_for_print[i][j] = string
        if i==j:
             container_for_print[i][j] = '--'

frame = pd.DataFrame(container_for_print)
frame['Score'] = score
frame['Place'] = places
print(frame)

