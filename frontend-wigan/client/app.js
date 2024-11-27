const API_URL = "http://localhost:8080/usuarios";

async function fetchUsuarios() {
    const response = await fetch(API_URL);
    const usuarios = await response.json();
    const tbody = document.querySelector("#usuarios tbody");
    tbody.innerHTML = "";
    usuarios.forEach(usuario => {
        const row = document.createElement("tr");
        row.innerHTML = `
            <td>${usuario.id}</td>
            <td>${usuario.hexa}</td>
            <td>
                <button onclick="deleteUsuario(${usuario.id})">Eliminar</button>
            </td>
        `;
        tbody.appendChild(row);
    });
}

async function addUsuario(event) {
    event.preventDefault();
    const hexa = document.getElementById("hexa").value;
    await fetch(API_URL, {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ hexa })
    });
    document.getElementById("usuario-form").reset();
    fetchUsuarios();
}

async function deleteUsuario(id) {
    await fetch(`${API_URL}/${id}`, { method: "DELETE" });
    fetchUsuarios();
}

document.getElementById("usuario-form").addEventListener("submit", addUsuario);

fetchUsuarios();
