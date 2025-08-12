package chtl.scanner;

public class BlockSpan {
    public final BlockType type;
    public final int startIndex;
    public final int endIndex;

    public BlockSpan(BlockType type, int startIndex, int endIndex) {
        this.type = type;
        this.startIndex = startIndex;
        this.endIndex = endIndex;
    }

    @Override
    public String toString() {
        return type + "@(" + startIndex + "," + endIndex + ")";
    }
}