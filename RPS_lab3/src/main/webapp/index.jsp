<%@ page import="javax.servlet.http.Cookie" %>
<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<!DOCTYPE html>
<html>
<head>
    <title>Home</title>
    <link rel="stylesheet" href="./css/style.css">
    <link rel="preconnect" href="https://fonts.googleapis.com">
    <link rel="preconnect" href="https://fonts.gstatic.com" crossorigin>
    <link href="https://fonts.googleapis.com/css2?family=Hanuman:wght@100..900&display=swap" rel="stylesheet">
    <style>
        :root {
            --login-hover-color: #505170;
        }
    </style>

</head>
<body>
    <header>
        <div class="header-container">
            <a class="header-btn left" href="/">Home</a>
            <div class="header-line"></div>
            <a class="header-btn right" href="FAQ.jsp">FAQ</a>
        </div>
        <div class="login-container">
            <%
                // Получаем userId из куки
                String userId = null;
                Cookie[] cookies = request.getCookies();
                if (cookies != null) {
                    for (Cookie cookie : cookies) {
                        if ("userId".equals(cookie.getName())) {
                            userId = cookie.getValue();
                            break;
                        }
                    }
                }

                // Проверяем если пользователь авторизован
                boolean isLoggedIn = (userId != null && !userId.isEmpty() && !"0".equals(userId));
            %>

            <% if (!isLoggedIn) { %>
            <!-- Кнопка Login если не авторизован -->
            <a class="login-btn" href="authorize.jsp">Login</a>
            <% } else { %>
            <!-- Кнопка Logout если авторизован -->
            <a class="logout-btn" href="javascript:void(0)" onclick="logout()">Logout</a>
            <% } %>
        </div>
    </header>

    <div class="app-body">
        <div class="app-control-panel">
            <div class="app-cp-manual">
                <a href="#">Ввести массив вручную</a>
            </div>
            <div class="app-cp-rand">
                <a href="#">Ввести случайный массив</a>
            </div>
            <div class="app-cp-sort">
                <a href="#">Отсортировать массив</a>
            </div>
            <div clss="app-cp-show">
                <a href="#">Получить все массивы пользователя</a>
            </div>
            <div class="app-cp-err">
                <p>bugs</p>
            </div>
        </div>
        <div class="app-display">

        </div>
    </div>

    <script>


        function logout() {
            //удаляем куки
            document.cookie = "userId=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;";

            //обновление страницы
            window.location.reload();
        }

        //проверка авторизации
        document.addEventListener('DOMContentLoaded', function() {
            if (<%=isLoggedIn%>) {
                document.documentElement.style.setProperty('--login-hover-color', '#c33838');
            } else {
                console.log("Пользователь не авторизован");
            }
        });

        //вспм. получение куки
        function getCookie(name) {
            const value = `; ${document.cookie}`;
            const parts = value.split(`; ${name}=`);
            if (parts.length === 2) return parts.pop().split(';').shift();
            return null;
        }
    </script>
</body>
</html>