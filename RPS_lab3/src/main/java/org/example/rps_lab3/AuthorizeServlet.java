package org.example.rps_lab3;

import javax.servlet.*;
import javax.servlet.annotation.*;
import javax.servlet.http.*;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.sql.SQLException;
import java.util.stream.Collectors;

@WebServlet("/authorizeServlet")
public class AuthorizeServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        response.setContentType("application/json; charset=UTF-8");
        response.setCharacterEncoding("UTF-8");

        PrintWriter out = response.getWriter();
        JSONObject jsonResponse = new JSONObject();

        try {
            //Получение json из jsp
            BufferedReader reader = request.getReader();
            String jsonString = reader.lines().collect(Collectors.joining());

            //Парс json
            JSONObject jsonRequest = new JSONObject(jsonString);
            String username = jsonRequest.optString("username", "");
            String password = jsonRequest.optString("password", "");

            //Вытаскиваем пользователя из бд
            DBConnect.start_connect();
            int authResult = DBConnect.authorize_user(username, password);

            if (authResult > 0) {
                //сохранение id в сессию
                HttpSession session = request.getSession();
                session.setAttribute("userId", authResult);
                session.setAttribute("username", username);

                //Сохранение id в куки
                Cookie userIdCookie = new Cookie("userId", String.valueOf(authResult));
                userIdCookie.setMaxAge(24 * 60 * 60); // 24 часа
                userIdCookie.setPath("/");
                response.addCookie(userIdCookie);
            }

            //Формируем ответ
            jsonResponse.put("status", authResult);
            out.print(jsonResponse.toString());

        } catch (Exception e) {
            jsonResponse.put("status", "error");
            jsonResponse.put("message", e.getMessage());
            out.print(jsonResponse.toString());
        } finally {
            //Отправка ответа
            out.flush();
        }
    }
}