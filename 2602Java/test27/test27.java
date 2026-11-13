package test27;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class test27 {
    public static void main(String[] args) {
        Path in = Paths.get("2602Java/test27/in.txt");
        Path out = Paths.get("2602Java/test27/out.txt");

        try (BufferedReader reader = Files.newBufferedReader(in, StandardCharsets.UTF_8);
             BufferedWriter writer = Files.newBufferedWriter(out, StandardCharsets.UTF_8)) {

            String line;
            int lineNo = 1;
            while ((line = reader.readLine()) != null) {
                writer.write(String.format("%3d: %s", lineNo, line));
                writer.newLine();
                lineNo++;
            }
        } catch (IOException e) {
            System.err.println("处理失败：" + e.getMessage());
        }
    }
}
