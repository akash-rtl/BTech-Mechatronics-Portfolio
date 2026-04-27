from llama_index import GPTSimpleVectorIndex
from flask import Flask, request

app = Flask(__name__)
index = GPTSimpleVectorIndex.load_from_disk('technical_index.json')

@app.route('/query', methods=['POST'])
def query():
    question = request.data.decode('utf-8')
    response = index.query(question)
    return str(response)

if __name__ == '__main__':
    app.run(port=5000)

