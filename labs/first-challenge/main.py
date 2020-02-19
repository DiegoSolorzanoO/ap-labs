# Diego Solórzano Ortiz A01422048

word = input('Input: ')
dt = []
counter = 0
mx = 0
pivot = 0
i = 0

while i!=len(word):
    if word[i] in dt:
        dt = []
        counter = 0
        pivot+=1
        i = pivot
    else:
        counter+=1
        dt.append(word[i])
        i+=1
    if counter>mx:
        mx = counter

print("Output: " + str(mx))
