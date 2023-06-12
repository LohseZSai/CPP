from typing import List, Tuple
from py3dbp21 import Packer, Bin, Item

def packing_algorithm(items: List[Tuple[str, str, str, Tuple[int, int, int], float, int, float, bool, str]]) -> Tuple[str, float, List[Tuple[str, str, Tuple[int, int, int], float]]]:
    # init packing function
    packer = Packer()

    # init bin
    box = Bin('example2',(11800, 2130, 2180), 23000, 0, 1)
    packer.addBin(box)

    # add items
    for item_data in items:
        partno, type_, typeof, whd, weight, level, loadbear, re, color = item_data
        packer.addItem(Item(partno, type_, typeof, whd, weight, level, loadbear, re, color))

    # calculate packing
    packer.pack(bigger_first=True, distribute_items=100, fix_point=True, number_of_decimals=0)

    # process result
    b = packer.bins[0]
    volume = b.width * b.height * b.depth
    fitted_items = [(item.partno, item.color, (item.width, item.height, item.depth), float(item.weight)) for item in b.items]
    space_utilization = round(sum(item.width * item.height * item.depth for item in b.items) / volume * 100, 2)
    residual_volume = float(volume) - sum(item.width * item.height * item.depth for item in b.items)
    return b.string(), space_utilization, fitted_items