with open(r'C:\Users\Scott\Desktop\yes.txt', 'r') as file:
    words = file.read().split()

letter_counts = {}

for word in words:
    for letter in word:
        if letter in letter_counts:
            letter_counts[letter] += 1
        else:
            letter_counts[letter] = 1

letter_counts = dict(sorted(letter_counts.items(), key=lambda x: ord(x[0])))
