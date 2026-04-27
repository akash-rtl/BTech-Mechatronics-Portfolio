Technical AI Chatbot
This chatbot utilizes a locally hosted Large Language Model (LLM) through Llama to answer technical queries. The chatbot is lightweight and efficient for text-based interactions.

Features:

Text-based question answering.
Uses a pre-built GPTSimpleVectorIndex for quick responses.
Requirements:

Install the Llama framework.
Download and configure a suitable LLM model (e.g., Llama 2, GPT-J) based on your requirements. These can be downloaded using the Llama ecosystem.
Pre-trained index file (technical_index.json).
How to Use:
Install and run the required LLM model locally using the Llama setup.
Start the Flask server by running the Python script.
Send a POST request to /query with the question as plain text in the request body.
Receive the response as plain text.
