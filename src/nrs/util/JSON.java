package nrs.util;

import org.json.simple.JSONObject;
import org.json.simple.JSONStreamAware;

import java.io.IOException;
import java.io.Writer;

public final class JSON {

    private JSON() {} //never

    public final static JSONStreamAware emptyJSON = prepare(new JSONObject());

    public static JSONStreamAware prepare(final JSONObject json) {
        return new JSONStreamAware() {
            private final char[] jsonChars = json.toJSONString().toCharArray();
            @Override
            public void writeJSONString(Writer out) throws IOException {
                out.write(jsonChars);
            }
        };
    }

    @SuppressWarnings("unchecked")
    public static JSONStreamAware prepareRequest(final JSONObject json) {
        json.put("protocol", 1);
        return prepare(json);
    }
    
    @SuppressWarnings("unchecked")
    public static void putNonNull(JSONObject json, String key, Object value)
    {
      if(value == null) return;
      json.put(key, value);
    }
}
