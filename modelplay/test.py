# def compare_words(word1, word2):
#     for i, (c1, c2) in enumerate(zip(word1, word2)):
#         if c1 == c2:
#             yield 'green'
#         elif c2 in word1:
#             yield 'orange'
#         else:
#             yield 'grey'

# print(list(compare_words('parer','panic')))
a = 'mana'
b = list(set(a))
c = list(a)
if list(set(a)) != list(a):
    print('yes')