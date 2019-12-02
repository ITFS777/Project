import xlrd
import os
os.system('cls') #清屏
# ------------------------------------------------------------
def find_min(seq):
    "返回当前序列的最小值和其索引"
    index=0
    i = 0
    while i < len(seq):
        if i == 0:
            Min = seq[i]
        if Min > seq[i]:
            Min = seq[i]
            index = i
        i += 1
    return Min,index
# ------------------------------------------------------------
def find_min_price(item_price_list):
    "返回购买单独当前商品所需最小价格及其索引"
    i = 0
    while i < len(item_price_list):
        if i == 0:
            min_price = item_price_list[i]+exp_price[i]
        if min_price > item_price_list[i]+exp_price[i]:
            min_price = item_price_list[i]+exp_price[i]
            min_index = i
        i += 1
    return min_price, min_index
# ------------------------------------------------------------
def get_price(item_list, shop, price, exp_price):
    "返回在指定商店购买指定部分商品的价格"
    if len(item_list)==0:
        return 0
    sum = exp_price[shop]
    for item in item_list:
        sum += price[item][shop]
    return sum

# ------------------------------------------------------------
# 声明数据格式
excel = xlrd.open_workbook('b.xlsx') # 打开的excel表格
table = excel.sheets()[0]            # 当前工作表
item_amount = 0                      # 商品数量
item_name = []                       # 商品名称列表
shop_amount = 0                      # 商店数量
shop_name = []                       # 商店名称列表
exp_price = []                       # 运费列表
price = []                           # 价格列表
# ------------------------------------------------------------
# 导入数据

i = 1
while table.cell(i, 0).value != '':
    # 导入商店名称
    shop_name.append(table.cell(i, 0).value)
    i += 1

i = 1
while table.cell(0, i).value != '':
    # 导入商品名称
    item_name.append(table.cell(0, i).value)
    i += 1

item_amount = len(item_name)  # 导入商品数量
shop_amount = len(shop_name)  # 导入商店数量

i = 1
while i <= shop_amount:
    # 导入快递费用
    exp_price.append(float(table.cell(i, item_amount+2).value))
    i += 1

i = 0
while i < item_amount:
    # 导入商品价格,将每件商品在每个商店的价格列表的存储在列表中
    price.append(list())
    j = 1
    while j <= shop_amount:
        price[i].append(float(table.cell(j, i+1).value))
        j += 1
    i += 1

del i
del j
# 回收变量
# ------------------------------------------------------------
# 计算最优方案
shop_buy=[[]for i in range(shop_amount)]   # 每个商店要买的商品

i=0
while i < item_amount:
    tmp=[]
    j=0
    while j<shop_amount:
      tmp.append(price[i][j]+(exp_price[j]/(len(shop_buy[j])+1)))
      j+=1
    shop_buy[find_min(tmp)[1]].append(i)
    del tmp
    i+=1
sum=0
i=0
while i<len(shop_buy):
    sum+=get_price(shop_buy[i],i,price,exp_price)
    i+=1
del i
del j
# 回收变量
# ------------------------------------------------------------
# 输出结果
print('最优方案如下')
i=0
while i<shop_amount:
    print(shop_name[i],':',sep='',end='')
    if len(shop_buy[i])==0:
        print(None)
        i+=1
        continue
    for item in shop_buy[i]:
        print('<',item_name[item],'>',sep='',end=' ')
    print()
    i += 1
print('最少价格为:','{:.2f}'.format(sum))



