<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>authorize</title>
    <meta http-equiv="Content-Security-Policy" content="script-src 'self' 'unsafe-inline'">
    <link rel="stylesheet" href="./css/style.css">
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Hanuman:wght@100..900&display=swap" rel="stylesheet">
</head>
<body>
<div class="authorize-header">
    <div class="home-container">
        <a href="/" class="home-but">HOME</a>
    </div>
</div>

<main>
    <div class="login-form">
        <h2>Авторизация пользователя</h2>

        <label for="username">Имя пользователя</label>
        <input type="text" id="username" name="username">
        <div class="error-msg" id="username-error">Введите имя пользователя</div>

        <label for="password">Пароль</label>
        <input type="password" id="password" name="password">
        <div class="error-msg" id="password-error">Введите пароль</div>

        <button class="login-authorize-btn">Войти</button>
    </div>

    <a href="/" class="register">Зарегистрироваться</a>
</main>
<script>
    document.addEventListener('DOMContentLoaded', function() {
        const loginBtn = document.querySelector('.login-authorize-btn');

        loginBtn.addEventListener('click', async (e) => {
            e.preventDefault();

            const username = document.getElementById('username').value.trim();
            const password = document.getElementById('password').value.trim();
            const userError = document.getElementById('username-error');
            const passError = document.getElementById('password-error');

            userError.classList.remove('active');
            passError.classList.remove('active');

            if (!username) {
                userError.textContent = "Введите имя пользователя";
                userError.classList.add('active');
                return;
            }
            if (!password) {
                passError.textContent = "Введите пароль";
                passError.classList.add('active');
                return;
            }

            try {
                console.log("Отправка данных на сервер:", { username, password });

                const requestData = {
                    username: username,
                    password: password
                };

                console.log("JSON данные:", JSON.stringify(requestData));

                const response = await fetch('authorizeServlet', {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/json; charset=UTF-8'
                    },
                    body: JSON.stringify(requestData)
                });

                console.log("Статус ответа:", response.status);

                if (!response.ok) {
                    throw new Error('HTTP error: ' + response.status);
                }

                const responseText = await response.text();
                console.log("Ответ от сервлета (текст):", responseText);

                const result = JSON.parse(responseText);
                console.log("Ответ от сервлета (JSON):", result);

                if (result.status === -1) {
                    passError.textContent = "Неверный пароль";
                    passError.classList.add('active');
                } else if (result.status === 0) {
                    userError.textContent = "Пользователь не найден";
                    userError.classList.add('active');
                } else if (typeof result.status === 'number' && result.status > 0) {
                    console.log("Успешный вход! ID пользователя:", result.status);
                    alert("Успешный вход! ID: " + result.status);

                    window.location.href = "index.jsp?user=" + result.status;
                } else {
                    userError.textContent = "Неизвестная ошибка сервера: " + result.status;
                    userError.classList.add('active');
                }

            } catch (err) {
                console.error("Ошибка при отправке запроса:", err);
                userError.textContent = "Ошибка соединения с сервером: " + err.message;
                userError.classList.add('active');
            }
        });
    });
</script>
</body>
</html>
