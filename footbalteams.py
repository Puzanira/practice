import numpy as np
import pandas as pd
num = 10

def get_places(scores):
    shape = scores.shape[0]
    num_score = [[scores[i], i] for i in range(shape)]
    num_score = sorted(num_score, key=lambda i: i[0], reverse = True)
    places = [0]*shape
    place = 1
    for i in range(shape-1):
        index = num_score[i][1]
        places[index] = place
        if (num_score[i][0] != num_score[i+1][0]):
            place += 1
    index = num_score[shape-1][1]
    places[index] = place
    return places

def prepare_to_print(matrix):
    shape = matrix.shape[0]
    container_for_print = [[0] * shape for i in range(shape)]
    for i in range(shape):
        for j in range(shape):
            string = str(matrix[i,j]) + ':' + str(matrix[j,i])
            container_for_print[i][j] = string
            if i==j:
                 container_for_print[i][j] = '--'
    return container_for_print

score_matrix = np.array(np.random.randint(0, 10, (num,num,)))
for i in range(num):
    score_matrix[i][i] = 0
score = score_matrix.sum(axis=1)

frame = pd.DataFrame(prepare_to_print(score_matrix))
frame['Score'] = score
frame['Place'] = get_places(score)
print(frame)
