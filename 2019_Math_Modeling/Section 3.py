import xlrd
import os
os.system('cls')  # 清屏
# ------------------------------------------------------------


def find_min(seq):
    "返回当前序列的最小值和其索引"
    index = 0
    i = 0
    while i < len(seq):
        if i == 0:
            Min = seq[i]
        if Min > seq[i]:
            Min = seq[i]
            index = i
        i += 1
    return Min, index
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
    if len(item_list) == 0:
        return 0
    sum = exp_price[shop]
    for item in item_list:
        sum += price[item][shop]
    return sum
# ------------------------------------------------------------


def could_buy(buy_list, item_min_price, money, sat_max,sat_map):
    "返回目前所拥有的的钱所能买到的满意度最大的商品的索引，如果没有则返回-1"
    i = 0
    while i < len(sat_max):
        if sat_map[sat_max[i]] in buy_list:
            i += 1
            continue
        if money > item_min_price[sat_map[sat_max[i]]]:
            return i
        i += 1
    return -1


# ------------------------------------------------------------
# 声明数据格式
excel = xlrd.open_workbook('data.xlsx')  # 打开的excel表格
table = excel.sheets()[0]            # 当前工作表
cost = 0                             # 预算
item_amount = 0                      # 商品数量
item_name = []                       # 商品名称列表
shop_amount = 0                      # 商店数量
shop_name = []                       # 商店名称列表
exp_price = []                       # 运费列表
price = []                           # 价格列表
sat = []                             # 满意度
sat_map = {}                         # 满意度-商品映射
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

cost = float(table.cell(shop_amount+2, 0).value) # 导入预算
cost_b = cost # 备份预算

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

i = 1
while i <= item_amount:
    # 导入商品满意度
    sat.append(int(table.cell(shop_amount+2, i).value))
    i += 1

del i
del j
# 回收变量
# ------------------------------------------------------------
# 计算每件商品最便宜的购买方案
shop_buy = [[]for i in range(shop_amount)]   # 每个商店要买的商品

i = 0
while i < item_amount:
    tmp = []
    j = 0
    while j < shop_amount:
        tmp.append(price[i][j]+(exp_price[j]/(len(shop_buy[j])+1)))
        j += 1
    shop_buy[find_min(tmp)[1]].append(i)
    del tmp
    i += 1

sum = 0
i = 0
while i < len(shop_buy):
    sum += get_price(shop_buy[i], i, price, exp_price)
    i += 1

del i
del j
# 回收变量
# ------------------------------------------------------------
# 处理数据
item_buy = [0 for i in range(item_amount)]    # 每个商品的购买商店
item_min_price = []                           # 每个商品的最少价格
sat_max = []                                  # 每个商品的最大单位满意度
i = 0
while i < item_amount:
    j = 0
    while j < shop_amount:
        if shop_buy[j].count(i) == 1:
            item_buy[i] = j
            break
        j += 1
    i += 1


i = 0
while i < item_amount:
    sat_max.append(sat[i]/(price[i][item_buy[i]] + (exp_price[item_buy[i]]/len(shop_buy[item_buy[i]]))))
    item_min_price.append(price[i][item_buy[i]]+(exp_price[item_buy[i]]/len(shop_buy[item_buy[i]])))
    i += 1
i = 0
while i < item_amount:
    sat_map[sat_max[i]] = i
    i += 1
del i
del j
# 回收变量
# ------------------------------------------------------------
# 生成解决方案
buy_list = []                                   # 要买的商品列表
item_info = []                                  # 要买的商品信息(商品,商店)
shop_info = [[] for i in range(shop_amount)]    # 每个商店购买的商品
tmp = could_buy(buy_list,item_min_price, cost, sat_max, sat_map)
while tmp != -1:
    cost -= item_min_price[tmp]
    tmp_info = [tmp,item_buy[tmp]]
    item_info.append(tuple(tmp_info))
    buy_list.append(tmp)
    tmp = could_buy(buy_list,item_min_price, cost, sat_max, sat_map)
    del tmp_info

i=0
for info in item_info:
    shop_info[info[1]].append(info[0])

del i
del tmp
# 回收变量
# ------------------------------------------------------------
# 结果处理
sat_sum = 0
for info in item_info:
    sat_sum += sat[info[0]]
# ------------------------------------------------------------
# 输出结果
print('最优方案如下')
i=0
while i<shop_amount:
    print(shop_name[i],':',sep='',end='')
    if len(shop_info[i])==0:
        print(None)
        i+=1
        continue
    for item in shop_info[i]:
        print('<',item_name[item],'>',sep='',end=' ')
    print()
    i += 1
print('最大满意度为:','{:.2f}'.format(sat_sum))
print('商品总预算为:','{:.2f}'.format(cost_b))
print('商品总价格为:','{:.2f}'.format(cost_b-cost))