const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors');

const app = express();
const PORT = 3000;

app.use(bodyParser.json());
app.use(cors());
app.use(express.static('public'));

// Tabela para guardar os dados
const Tabela_Valores = {};

// Rota para receber os valores do front
app.post('/submit', (req, res) => {
    const { value } = req.body;

    if (!value) {
        return res.status(400).json({ error: 'Valor não enviado!' });
    }

    if (Tabela_Valores[value]) {
        Tabela_Valores[value] += 1;
    } else {
        Tabela_Valores[value] = 1;
    }

    // Retorna todos os valores para o front
    res.json({ values: Tabela_Valores });
});

// Inicia o servidor
app.listen(PORT, () => {
    console.log(`Servidor rodando em http://localhost:${PORT}`);
});