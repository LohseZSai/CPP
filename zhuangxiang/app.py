from flask import Flask, request, render_template
import PackingAlgorithm

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/packing', methods=['POST'])
def packing():
    types = request.form.getlist('type')
    nums = request.form.getlist('num')
    shapes = request.form.getlist('shape')
    whds = request.form.getlist('whd')
    weights = request.form.getlist('weight')
    levels = request.form.getlist('level')
    loadbears = request.form.getlist('loadbear')
    reversibles = request.form.getlist('reversible')
    colors = request.form.getlist('color')

    goods = []
    for i in range(len(types)):
        goods.append({
            'type': types[i],
            'num': int(nums[i]),
            'shape': shapes[i],
            'whd': [float(x) for x in whds[i].split(',')],
            'weight': float(weights[i]),
            'level': int(levels[i]),
            'loadbear': float(loadbears[i]),
            'reversible': bool(reversibles[i]),
            'color': colors[i]
        })

    packer = PackingAlgorithm()
    result = packer.pack(goods)

    return render_template('index.html', result=result)

if __name__ == '__main__':
    app.run(debug=True)