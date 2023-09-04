import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.FileInputStream;
import javax.imageio.ImageIO;

/**
 *
 * @author LWJGL2
 */
public class GlyphConverter {

    private static String chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789?/.,~";

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws Throwable {
        BufferedImage image = new BufferedImage(256, 256, BufferedImage.TYPE_BYTE_GRAY);
        {
            Graphics g = image.getGraphics();
            g.setColor(Color.white);
//            g.setFont(getFont("consolas.ttf").deriveFont(0, 20f));
            g.setFont(new Font("Monospaced", 0, 9));

            chars = "";
            for (int i = 32; i < 127; i++) {
                chars += (char) i;
            }
            System.out.println((int) '\n');

            System.out.println(chars);
// font 14
//            final int w = 12;
//            final int h = 20;
//            final int yOffset = 5;

// font 12
//            final int w = 8;
//            final int h = 14;
//            final int yOffset = 3;
// font 8
            final int w = 5;
            final int h = 10;
            final int yOffset = 3;
            boolean[][] bits = new boolean[chars.length()][w * h];
            int x = 0;
            int y = 1;
            for (int i = 0; i < chars.length(); i++) {
                if (x >= (image.getWidth() / w)) {
                    x = 0;
                    y++;
                }
                g.drawString(String.valueOf(chars.charAt(i)), x * w, y * h - yOffset);
                x++;
            }
            x = 0;
            y = 0;
            for (int i = 0; i < chars.length(); i++) {
                if (x >= (image.getWidth() / w)) {
                    x = 0;
                    y++;
                }

                BufferedImage sub = image.getSubimage(x * w, y * h, w, h);

                int index = chars.charAt(i) - 32;

                boolean[] imageBits = new boolean[w * h];
                {
                    for (int xx = 0; xx < w; xx++) {
                        for (int yy = 0; yy < h; yy++) {
                            int[] pixel = new int[4];
                            sub.getRaster().getPixel(xx, yy, pixel);
                            imageBits[xx * h + yy] = pixel[0] > 0;
                        }
                    }
                }
                bits[index] = imageBits;

                ImageIO.write(sub, "PNG", new File("aga/" + index + ".png"));

                x++;
            }

            x = 0;
            y = 1;
            for (int i = 0; i < chars.length(); i++) {
                if (x >= (image.getWidth() / w)) {
                    x = 0;
                    y++;
                }

//                g.fillRect(0, y * h, image.getWidth(), 1);
//                g.fillRect(x * w, 0, 1, image.getHeight());
                x++;
            }

            StringBuffer buf = new StringBuffer("#define GLYPH_COUNT " + bits.length + "\n#define GLYPH_SIZE " + bits[0].length + "\n#define GLYPH_W " + w + "\n#define GLYPH_H " + h + "\n\nconst bool bits[GLYPH_COUNT][GLYPH_SIZE] PROGMEM = {\n");

            for (int i = 1; i < bits.length; i++) { // skip space
                boolean[] glyph = bits[i];

                buf.append("\t{");
                {
                    for (int j = 0; j < glyph.length; j++) {
                        buf.append(glyph[j] ? "1" : "0");
                        if (j < glyph.length - 1) {
                            buf.append(",");
                        }
                    }
                }
                buf.append("},\n");

            }

            buf.append("};");

            System.out.println(buf);

        }
        ImageIO.write(image, "PNG", new File("output.png"));
    }

    private static Font getFont(String name) throws Exception {
        Font font = Font.createFont(Font.TRUETYPE_FONT, new FileInputStream(name));
        return font;
    }
}
