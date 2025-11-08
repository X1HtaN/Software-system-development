package org.example.rps_lab3;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class DBConnect {
    private static Connection connection = null;
    private static Statement statement = null;
    private static ResultSet resultSet = null;

    final static String DBUSER = "35zcYNxe8LpiaG3.root";
    final static String DBPWD = "Gp54uAM9VUu55Xvf";
    final static String DBURL = "jdbc:mysql://gateway01.eu-central-1.prod.aws.tidbcloud.com:4000/service";

    public static void start_connect() throws ClassNotFoundException, SQLException {
        Class.forName("com.mysql.cj.jdbc.Driver");

        connection = null;
        connection = DriverManager.getConnection(DBURL, DBUSER, DBPWD);
        if(connection != null) {
            System.out.println("Connected to the database successfully");
        } else {
            System.out.println("Failed to connect to database");
        }

        statement = null;
        statement = connection.createStatement();
        if(statement != null) {
            System.out.println("Created statement successfully");
        } else {
            System.out.println("Failed to create statement");
        }
    }

    public static int authorize_user(String username, String password) throws SQLException {
        String query = "SELECT id, password FROM users WHERE username = ?";

        try (PreparedStatement pstmt = connection.prepareStatement(query)) {
            pstmt.setString(1, username);
            ResultSet resultSet = pstmt.executeQuery();

            if (resultSet.next()) {
                String dbPassword = resultSet.getString("password");
                int userId = resultSet.getInt("id");

                if (password.equals(dbPassword)) {
                    return userId; //все гуд (всегда 1 возвращает)
                } else {
                    return -1; //невенрый пароль
                }
            } else {
                return 0; //пользователь не найден
            }
        } catch (SQLException e) {
            return 0;
        }
    }

    public static int registrate_user(String username, String password) throws SQLException {
        String query = "INSERT INTO users (username, password) VALUES (?, ?)";

        try (PreparedStatement pstmt = connection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS)) {
            pstmt.setString(1, username);
            pstmt.setString(2, password);

            try {
                ResultSet resultSet = pstmt.getGeneratedKeys();
                resultSet.next();
                int userId = resultSet.getInt(1);
                System.out.println(userId);
                return userId;
            } catch (SQLException e) {
                return 0; //ошибка запроса
            }

        } catch (SQLException e){
            return -1; //не удалось создать стейтмент
        }
    }

    public static int upload_list(int id, List<Integer> list){
        return 0;
    }
}
