<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>registration</title>
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
        <h2>Регистрация пользователя</h2>

        <label for="username">Имя пользователя</label>
        <input type="text" id="username" name="username">
        <div class="error-msg" id="username-error">Введите имя пользователя</div>

        <label for="password">Пароль</label>
        <input type="password" id="password" name="password">
        <div class="error-msg" id="password-error">Введите пароль</div>

        <button class="registration-btn">Зарегистрироваться</button>
    </div>

    <a href="/authorize.jsp" class="register">Авторизация</a>
</main>
<script>
    document.addEventListener('DOMContentLoaded', function() {
        const loginBtn = document.querySelector('.registration-btn');

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

            try{
                console.log("Отправка данных на сервер:", { username, password });

                const requestData = {
                    username: username,
                    password: password
                };

                console.log("JSON данные:", JSON.stringify(requestData));

                const response = await fetch('regitrateServlet', {
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

                if(result.status === 0){
                    userError.textContent = "Не удалось создать стейтмент на сервере";
                    userError.classList.add('active');
                } else if (result.status === -1){
                    userError.textContent = "Не удалось отправить запрос на базу данных сервера";
                    userError.classList.add('active');
                } else if (result.status === -2){
                    userError.textContent = "Такой пользователь уже существует";
                    userError.classList.add('active');
                } else if (typeof result.status === 'number' && result.status > 0){
                    console.log("Успешная регистрация! ID пользователя:", result.status);

                    window.location.href = "index.jsp";
                }

            } catch(err) {
                console.error("Ошибка при отправке запроса:", err);
                userError.textContent = "Ошибка соединения с сервером: " + err.message;
                userError.classList.add('active');
            }
        });
    });
</script>
</body>
</html>
