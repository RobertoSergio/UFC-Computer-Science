const form = document.getElementById('valueForm');
const resultDiv = document.getElementById('result');
const tableBody = document.querySelector('#dataTable tbody');

// função para criar uma alerta de sucesso ou de erro
const Alertapopup = (status, message) => {
    const alertContainer = document.createElement('div');
    alertContainer.className = `fixed bottom-5 right-5 px-6 py-4 rounded-lg shadow-lg text-lg ${
        status === 'success' ? 'bg-green-500 text-white' : 'bg-red-500 text-white'
    }`;
    alertContainer.textContent = message;

    document.body.appendChild(alertContainer);

    // Alerta some depois de 2 segundos
    setTimeout(() => {
        alertContainer.remove();
    }, 2000);
};

// Função para atualizar a tabela
function AtualizarTabela(values) {
    tableBody.innerHTML = '';

    Object.entries(values).forEach(([value, count]) => {
        const row = document.createElement('tr');
        row.innerHTML = `
            <td>${value}</td>
            <td>${count}</td>
        `;
        tableBody.appendChild(row);
    });
}

// Função para enviar os dados para o back
form.addEventListener('submit', async (event) => {
    event.preventDefault();

    const valueInput = document.getElementById('valueInput');
    const value = valueInput.value.trim();

    if (!value) {
        Alertapopup('error', 'Por favor, preencha o campo com um valor válido!');
        return;
    }

    try {
        const response = await fetch('http://localhost:3000/submit', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({ value }),
        });

        if (!response.ok) {
            throw new Error('Erro ao enviar o valor para o servidor.');
        }

        const data = await response.json();

        // Atualiza a tabela
        AtualizarTabela(data.values);

        // Exibe um alerta de sucesso
        Alertapopup('success', `O valor "${value}" foi enviado com sucesso.`);
    } catch (error) {
        Alertapopup('error', `Erro: ${error.message}`);
    }

    // Limpa o campo de entrada
    valueInput.value = '';
});
