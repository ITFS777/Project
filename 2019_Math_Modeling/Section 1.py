import os
from itertools import combinations
from itertools import permutations
# ------------------------------------------------------------


def list_min(seq):
    "返回列表最小值"
    min = seq[0]
    for x in seq:
        if min > x:
            min = x
    return min
# ------------------------------------------------------------


def get_price(book_name_seq, book_price_dict, shop_name, exp_price_dict):
    "返回在指定商店购买指定部分书籍的价格"
    sum = exp_price_dict[shop_name]
    for name in book_name_seq:
        sum += book_price_dict[shop_name][name]
    return sum
# ------------------------------------------------------------


def find_min_shop(book_name, book_price_dict, shop_name_dict, exp_price_dict):
    "返回当前书籍价格+运费最便宜的商店的价格"
    min_name = shop_name_dict[0]
    for name in shop_name_dict:
        if (book_price_dict[min_name][book_name]) > (book_price_dict[name][book_name]):
            min_name = name
    return book_price_dict[min_name][book_name]+exp_price_dict[min_name],min_name

# ------------------------------------------------------------


def find_unselected(book_name_s, book_name):
    "返回列表中剩余的书籍名称"
    tmp_list = []
    for name in book_name:
        tmp_list.append(name)
    for name in book_name_s:
        if name in tmp_list:
            tmp_list.remove(name)
    return tmp_list


# ------------------------初始化------------------------------
os.system("cls")  # 清屏

book_name = ('B1', 'B2', 'B3', 'B4', 'B5')  # 书籍名称

shop_name = ('T', 'J', 'P', 'D', 'B', 'Y')  # 商店名称

T = {'B1': 18, 'B2': 39, 'B3': 29, 'B4': 48, 'B5': 59}
J = {'B1': 24, 'B2': 45, 'B3': 23, 'B4': 54, 'B5': 44}
P = {'B1': 22, 'B2': 45, 'B3': 23, 'B4': 53, 'B5': 53}
D = {'B1': 28, 'B2': 47, 'B3': 17, 'B4': 57, 'B5': 47}
B = {'B1': 24, 'B2': 42, 'B3': 24, 'B4': 47, 'B5': 59}
Y = {'B1': 27, 'B2': 48, 'B3': 20, 'B4': 55, 'B5': 53}
book_price = {'T': T, 'J': J, 'P': P, 'D': D, 'B': B, 'Y': Y}
# 书籍价格

exp_price = {'T': 10, 'J': 15, 'P': 15, 'D': 10, 'B': 10, 'Y': 15}    # 运费列表
shop_amount = 6  # 商店数量
book_amount = 5  # 书籍数量

# -----------------------导入数据--------------------------------
book_price_list = []
i = 0
while i < book_amount:
    book_price_list.append(list())
    for name in shop_name:
        book_price_list[i].append(book_price[name][book_name[i]])
    i += 1
del i
# 回收变量

# 将每本书在不同商店的价格转为列表
# ------------------------------------------------------------
i = 0

while i < shop_amount:
    sum=get_price(book_name, book_price, shop_name[i], exp_price)
    if i==0:
        min=sum
        book_shop=shop_name[i]
    if min>sum:
        min=sum
        book_shop=shop_name[i]
    i += 1

print('------------------------------')
print('min(5:0):\t', min, sep='')  # 所有书都在同一家商店购买
print()
for book in book_name:
    print(book,':',book_shop,sep='',end=' ')
print('\n------------------------------')

del i
del min
del sum
del book_shop
# 回收变量
# ------------------------------------------------------------
S_6C2 = list(permutations(iter(list(shop_name)), 2))
# 选择两家店
S_6C3 = list(permutations(iter(list(shop_name)), 3))
# 选择三家店
S_6C4 = list(permutations(iter(list(shop_name)), 4))
# 选择四家店
B_5C4 = list(combinations(iter(list(book_name)), 4))
# 选择四本书
B_5C3 = list(combinations(iter(list(book_name)), 3))
# 选择三本书
B_5C2 = list(combinations(iter(list(book_name)), 2))
# 选择两本书
UB_5C4 = []
UB_5C3 = []
UB_5C2 = []
B_5C3_3C2 = []
UB_5C3_3C2 = []
B_5C2_2C1 = []
UB_5C2_2C1 = []
for book_list in B_5C4:
    UB_5C4.append(tuple(find_unselected(book_list, book_name)))
for book_list in B_5C3:
    UB_5C3.append(tuple(find_unselected(book_list, book_name)))
    B_5C3_3C2.append(list(combinations(iter(list(book_list)), 2)))
for book_list in B_5C2:
    UB_5C2.append(tuple(find_unselected(book_list, book_name)))
    B_5C2_2C1.append(list(combinations(iter(list(book_list)), 1)))

i = 0
while i < len(B_5C3):
    UB_5C3_3C2.append(list())
    for state in B_5C3_3C2[i]:
        UB_5C3_3C2[i].append(tuple(find_unselected(state, B_5C3[i])))
    i += 1

i = 0
while i < len(B_5C2):
    UB_5C2_2C1.append(list())
    for state in B_5C2_2C1[i]:
        UB_5C2_2C1[i].append(tuple(find_unselected(state, B_5C2[i])))
    i += 1
# ------------------------------------------------------------
count=0
book_shop={}

for shop_list in S_6C2:  # 其中四本和剩余一本分别在两家商店购买
    i = 0
    while i < len(B_5C4):
        sum = 0
        sum += get_price(B_5C4[i], book_price, shop_list[0], exp_price)
        sum += get_price(UB_5C4[i], book_price, shop_list[1], exp_price)
        if count==0:
            min=sum
            for name in B_5C4[i]:
                book_shop[name]=shop_list[0]
            for name in UB_5C4[i]:
                book_shop[name]=shop_list[1]
        if min>sum:
            min=sum
            book_shop.clear()
            for name in B_5C4[i]:
                book_shop[name]=shop_list[0]
            for name in UB_5C4[i]:
                book_shop[name]=shop_list[1]
        i += 1
    count +=1

print('min(4:1):\t', min, sep='')
print()
for book in book_name:
    print(book, book_shop[book],sep=':',end=' ')
print('\n------------------------------')

del i
del min
del sum
del book_shop
# 回收变量
# ------------------------------------------------------------
count=0
book_shop={}

for shop_list in S_6C2:  # 其中三本和剩余两本分别在两家商店购买
    i = 0
    while i < len(B_5C3):
        sum = 0
        sum += get_price(B_5C3[i], book_price, shop_list[0], exp_price)
        sum += get_price(UB_5C3[i], book_price, shop_list[1], exp_price)
        if count==0:
            min=sum
            for name in B_5C3[i]:
                book_shop[name]=shop_list[0]
            for name in UB_5C3[i]:
                book_shop[name]=shop_list[1]
        if min>sum:
            min=sum
            book_shop.clear()
            for name in B_5C3[i]:
                book_shop[name]=shop_list[0]
            for name in UB_5C3[i]:
                book_shop[name]=shop_list[1]
        i += 1
    count+=1

print('min(3:2):\t', min, sep='')
print()
for book in book_name:
    print(book, book_shop[book],sep=':',end=' ')
print('\n------------------------------')

del i
del sum
del min
del count
del book_shop
# 回收变量
# ------------------------------------------------------------
book_shop={}
count=0

for shop_list in S_6C3:
    i = 0
    while i < len(UB_5C3):
        j = 0
        while j < len(B_5C3_3C2[0]):
            sum = 0
            sum += get_price(UB_5C3[i], book_price, shop_list[0], exp_price)
            sum += get_price(B_5C3_3C2[i][j],book_price, shop_list[1], exp_price)
            sum += get_price(UB_5C3_3C2[i][j],book_price, shop_list[2], exp_price)
            if count==0:
                min=sum
                for name in UB_5C3[i]:
                    book_shop[name]=shop_list[0]
                for name in B_5C3_3C2[i][j]:
                    book_shop[name]=shop_list[1]
                for name in UB_5C3_3C2[i][j]:
                    book_shop[name]=shop_list[2]
            if min>sum:
                min=sum
                book_shop.clear()
                for name in UB_5C3[i]:
                    book_shop[name]=shop_list[0]
                for name in B_5C3_3C2[i][j]:
                    book_shop[name]=shop_list[1]
                for name in UB_5C3_3C2[i][j]:
                    book_shop[name]=shop_list[2]
            j += 1
        i += 1
    count +=1

print('min(2:2:1):\t', min, sep='')
print()
for book in book_name:
    print(book, book_shop[book],sep=':',end=' ')
print('\n------------------------------')

del i
del j
del sum
del min
del count
del book_shop
# 回收变量
# ------------------------------------------------------------
count=0
book_shop={}

for shop_list in S_6C3:
    i = 0
    while i < len(B_5C2):
        sum = 0
        sum += get_price(UB_5C2[i], book_price, shop_list[0], exp_price)
        sum += get_price(B_5C2_2C1[i][0], book_price, shop_list[1], exp_price)
        sum += get_price(UB_5C2_2C1[i][0], book_price, shop_list[2], exp_price)
        if count==0:
            min=sum
            for name in UB_5C2[i]:
                book_shop[name]=shop_list[0]
            for name in B_5C2_2C1[i][0]:
                book_shop[name]=shop_list[1]
            for name in UB_5C2_2C1[i][0]:
                book_shop[name]=shop_list[2]
        if min>sum:
            min=sum
            book_shop.clear()
            for name in UB_5C2[i]:
                book_shop[name]=shop_list[0]
            for name in B_5C2_2C1[i][0]:
                book_shop[name]=shop_list[1]
            for name in UB_5C2_2C1[i][0]:
                book_shop[name]=shop_list[2]
        i += 1
    count+=1

print('min(3:1:1):\t', min, sep='')
print()
for book in book_name:
    print(book, book_shop[book],sep=':',end=' ')
print('\n------------------------------')

del i
del sum
del min
del count
del book_shop
# 回收变量
# ------------------------------------------------------------
book_shop=[]
count=0
tmp_name=[0]

for shop_list in S_6C4:
    j=0
    for state in B_5C3:
        i=0
        sum=0
        book_shop.append({})
        while i < len(state):
            tmp_name[0]=state[i]
            sum+=get_price(tmp_name,book_price,shop_list[i],exp_price)
            book_shop[count][state[i]]=shop_list[i]
            i+=1
        sum+=get_price(UB_5C3[j],book_price,shop_list[3],exp_price)
        for book in UB_5C3[j]:
            book_shop[count][book]=shop_list[3]
        count+=1
        j+=1

min=0
min_i=0
i=0
while i < count:
    sum=0
    for book,shop in book_shop[i].items():
        tmp_name[0]=book
        sum+=get_price(tmp_name,book_price,shop,exp_price)
    if i==0:
        min=sum
    if min>sum:
        min=sum
        min_i=i
    i+=1

print('min(2:1:1:1):\t',min,sep='')
print()
for book in book_name:
    print(book, book_shop[min_i][book],sep=':',end=' ')
print('\n------------------------------')

del i
del j
del sum
del min
del min_i
del tmp_name
del book_shop
# 回收变量
# ------------------------------------------------------------
book_shop={}
book_shop.setdefault(book_name)
sum=0
for name in book_name:
    min_price,min_shop=find_min_shop(name, book_price, shop_name, exp_price)
    sum+=min_price
    book_shop[name]=min_shop

print('min(1:1:1:1:1):\t', sum, sep='')  # 每本书都在不同的商店购买
print()
for book in book_name:
    print(book, book_shop[book],sep=':',end=' ')
print('\n------------------------------')
del sum
del min_shop
del min_price
del book_shop
# 回收变量
# ------------------------------------------------------------